(function ($) {

Drupal.training = {};
Drupal.behaviors.training = {
  attach: function (context) {
    var wid;
    var container;
    var links;
  
    // Select the launch links
    links = $('a.launch-webinar:not(.processed)', context);
    $(links).addClass('processed');
    
    // React when launch links are clicked
    $(links).click(function() {
      // Extract the webinar ID
      wid = $(this).attr('id').replace(/[^0-9]/g, '');
      
      // Do not proceed without a wid
      if (!wid) {
        alert(Drupal.t('Cannot initialize the webinar'));
        return;
      }
      
      // Replace link with the loading indicator
      container = $(this).parents('.webinar-message');
      $(this).remove();
      $(container).find('.webinar-loading').show();
      
      // Fetch the user's data for this webinar
      $.ajax({
        url: Drupal.settings.basePath + '?q=webinar/getdata',
        type: "GET",
        cache: "false",
        dataType: "json",
        data: {wid: wid},
        success: function (response) {
          if (!response.success) {
            $(this).error();
          }
          else {
            if (Drupal.training.launchWebinar(wid, response)) {
              $(container).html(Drupal.t('Webinar launched!'));
            }
            else {
              $(container).find('.webinar-loading').html(Drupal.t('You must reload this page to launch the webinar'));
            }
          }
        },
        error: function () {
          alert(Drupal.t('An error occurred trying to retrieve your course data from the server.'));
          location.reload();
        }
      });
      
      return;
    });
  }
};

})(jQuery);

/**
 * Launch a given webinar by ID
 * 
 * @param wid
 *   The webinar ID
 * @param response
 *   The response from the server containing user data
 */
Drupal.training.launchWebinar = function (wid, response) {
  var lessonURL = Drupal.settings.gsa_training.training_path;
  
  // Initialize scorm
  scormData.init();
  
  // Store the webinar ID
  scormData.wid = wid;
  
  // Set the user authentication status
  scormData.authenticated = response.authenticated;
  
  // Set the scorm state
  if (response.data) {
    // Detect if the user has already completed this course
    if (response.data.completion_status == 'completed') {
      if (response.data.success_status != 'failed') {
        alert(Drupal.t('You have already successfully completed this webinar'));
        return false;
      }
    }
    
    scormData.entry = "resume";
    scormData.suspend_data = response.data.suspend_data;
    scormData.location = response.data.location;
    scormData.completion_status = response.data.completion_status;
    scormData.success_status = response.data.success_status;
    scormData.last_saved = response.data;
  }
  
  // Set a message if the user is not authenticated
  if (!response.authenticated) {
    var proceed = confirm(Drupal.t('Reminder: Since you are not logged in, your course data cannot be saved or reloaded, and you will not be awarded credit for taking this course. We recommend you log in or register for a free account before proceeding.\n\nAre you sure you want to continue?'));
    if (proceed == false) {
      return false;
    }
  }

  // Launch the webinar
  lesson.open(lessonURL);
  
  // Kill webinar on page unload
  $(window).unload(function() {
    if (lesson) {
      lesson.close();
    }
  });
  
  return true;
}

Drupal.training.transmit = function() {
  // If the user is not authenticated, don't save
  if (!scormData.authenticated) {
    dbWin.out('Transmit', 'Save skipped - user unauthenticated');
    return;
  }
  
  // Build a data object with the values we need
  var data = {
    wid: scormData.wid,
    suspend_data: scormData.suspend_data,
    completion_status: scormData.completion_status,
    location: scormData.location,
    success_status: scormData.success_status,
    scaled_score: scormData.scaled_score
  }
  
  // If the data isn't marked as completed, allow the lock to take effect
  if (data.completion_status != 'completed') {
    // Check if the scorm data object is locked
    // Being locked indicates that a save operation is still
    // in progress
    if (scormData.locked) {
      // Skip this save
      dbWin.out('Transmit', 'Save skipped - save operation still in progress');
      return;
    }
    else {
      // Lock down the object
      scormData.locked = true;
    }
  }
  
  // Only proceed if the data is different from the last save
  if (objectIsSame(data, scormData.last_saved)) {
    dbWin.out('Transmit', 'Save skipped - data object has not changed');
    return;
  }

  // Transmit the object to the server to be saved
  $.ajax({
    url: Drupal.settings.basePath + '?q=webinar/savedata',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: data,
    success: function(response) {
      if (!response.success) {
        $(this).error();
      }
      else {
        dbWin.out('Transmit', 'Save successful');
        scormData.last_saved = data;
        scormData.locked = false;
      }
    },
    error: function() {
      dbWin.out('Transmit', 'Save failed');
      alert(Drupal.t('An error has occurred while trying to save your course data.')); 
      scormData.locked = false; 
    }
  }); 
}

/**
 * Determine if two objects are the same
 */
function objectIsSame(obj1, obj2) {
  function size(obj) {
    var size = 0;
    for (var keyName in obj) {
      if (keyName != null) {
        size++;
      }
    }
    return size;
  }

  if (size(obj1) != size(obj2)) {
    return false;
  }

  for (var keyName in obj1) {
    var value1 = obj1[keyName];
    var value2 = obj2[keyName];

    if (typeof value1 != typeof value2) {
      return false;
    }

    // For jQuery objects:
    if (value1 && value1.length && (value1[0] !== undefined && value1[0].tagName)) {
      if (!value2 || value2.length != value1.length || !value2[0].tagName || value2[0].tagName != value1[0].tagName) {
        return false;
      }
    }
    else if (typeof value1 == 'function' || typeof value1 == 'object') {
      var equal = compare(value1, value2);
      if (!equal) {
        return equal;
      }
    }
    else if (value1 != value2) {
      return false;
    }
  }
  return true;
}

/**
 * The lesson window
 */
var lesson = {
  window: null,
  URL: "",
  active: false,
  open: function (pURL) {
    this.URL = pURL;
    this.window = window.open(pURL, "Lesson",
    	"menu=0,location=0"
    	+ ",width=980,height=800"
    	+ ",scrollbars=1,resizable=1");
    if (null != this.window) {
      this.active = true;
    }
  }
  ,
  close: function () {
    if (this.active && null != this.window) {
      this.window.close();
    }
    return;
  }
};

/**
 * Pad a string or number with zeros to the left
 */
function pad(number, length) {
  var str = '' + number;
  while (str.length < length) {
    str = '0' + str;
  }
  return str;
}

/**
 * Debugging console
 */
var dbWin = {
  out: function (op, msg, giveUp) {
    // Turn debugging on or off
    var enableDebug = false;
    
    if (enableDebug) {
      if (console && console.log) {
        console.log('[' + op + '] ' + msg);
      }
    }
    return;
  }
};

/**
 * The SCORM data object
 */
var scormData = {
  _version: 1.0,
  completion_status: "unknown",
  entry: "ab-initio",
  exit: "",
  location: null,
  mode: "normal",
  progress_measure: "0",
  suspend_data: null,
  scaled_score: null,
  success_status: "unknown",
  learner_id: null,
  learner_name: null,
  scaled_passing_score: "0.70",
  wid: 0,
  last_saved: {},
  locked: false,
  onLocationChange: null,
  onSuspendDataChange: null,
  authenticated: false,
  init: function () {
    this.completion_status = "unknown";
    this.entry = "ab-initio"
    this.exit = ""
    this.location = null
    this.mode = "normal"
    this.progress_measure = "0"
    this.suspend_data = null
    this.scaled_score = null
    this.success_status = "unknown"
    this.wid = 0
    this.learner_id = null
    this.learner_name = null
    this.last_saved = {}
    this.locked = false
    this.scaled_passing_score = Drupal.settings.gsa_training.passing_score
    this.authenticated = false
    return;
  }
};

/**
 * Implementation of the SCORM API
 */
window.API_1484_11 = {
  status: "",
  _NoError: 0,
  _GeneralException: 101,
  _GeneralInitializationFailure: 102,
  _AlreadyInitialized: 103,
  _ContentInstanceTerminated: 104,
  _GeneralTerminationFailure: 111,
  _TerminationBeforeInitialization: 112,
  _TerminationAfterTermination: 113,
  _ReceivedDataBeforeInitialization: 122,
  _ReceivedDataAfterTermination: 123,
  _StoreDataBeforeInitialization: 132,
  _StoreDataAfterTermination: 133,
  _CommitBeforeInitialization: 142,
  _CommitAfterTermination: 143,
  _GeneralArgumentError: 201,
  _GeneralGetFailure: 301,
  _GeneralSetFailure: 351,
  _GeneralCommitFailure: 391,
  _UndefinedDataModelElement: 401,
  _UnimplementedDataModelElement: 402,
  _DataModelElementValueNotInitialized: 403,
  _DataModelElementIsReadOnly: 404,
  _DataModelElementIsWriteOnly: 405,
  _DataModelElementTypeMismatch: 406,
  _DataModelElementValueOutOfRange: 407,
  last_retVal: this._NoError,
  retVal: function (pRet) {
    this.last_retVal = pRet;
    return pRet;
  },
  resetInterface: function () {
    this.status = "";
    if ("suspend" == scormData.exit) { // Just leave the data as we found it...
    }
    else {
      // Here it gets sticky... if they weren't suspended do we
      // want to leave old data around?
      scormData.init();
    }

    return;
  },
  Initialize: function (pParam) {
    var vRetVal;
    // Assume no problem...
    vRetVal = "true";
    this.retVal(this._NoError);
    // Now check for erros
    if ("open" == this.status) {
      this.retVal(this._AlreadyInitialized);
      vRetVal = "false";
    }
    if ("closed" == this.status) {
      this.retVal(this._ContentInstanceTerminated);
      vRetVal = "false";
    }
    if (pParam != "") {
      this.retVal(this._GeneralArgumentError);
      vRetVal = "false";
    }
    if (this._NoError == this.last_retVal) {
      this.status = "open";
    }
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("Init", "Initialize():" + "  status '" + this.status + "'" + "  ret value '" + vRetVal + "'" + vErrCode);
    }
    return vRetVal;
  },
  Terminate: function (pParam) {
    var vRetVal;
    // Assume no problem...
    vRetVal = "true";
    this.retVal(this._NoError);
    // Now check for errors
    if ("" == this.status) {
      this.retVal(this._TerminationBeforeInitialization);
      vRetVal = "false";
    }
    if ("closed" == this.status) {
      this.retVal(this._TerminationAfterTermination);
      vRetVal = "false";
    }
    if (pParam != "") {
      this.retVal(this._GeneralArgumentError);
      vRetVal = "false";
    }
    if (this._NoError == this.last_retVal) {
      this.status = "closed";
    }
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("Term", "Terminate():" + "  status '" + this.status + "'" + "  ret value '" + vRetVal + "'" + vErrCode);
    }
    lesson.window.close();
    return vRetVal;
  },
  DebugOut: function (pMessage) {
    if (dbWin) {
      dbWin.out("Debug", pMessage);
    }
    return "true";
  },
  GetValue: function (pValueName) {
    var vRetVal;
    var vDispName;
    var vDispExtension;
    var vDispIdx;

    // Check for errors
    if ("" == this.status) {
      this.retVal(this._ReceivedDataBeforeInitialization);
      vRetVal = "";
      return vRetVal;
    }
    if ("closed" == this.status) {
      this.retVal(this._ReceivedDataAfterTermination);
      vRetVal = "";
      return vRetVal;
    }
    if ("" == pValueName) {
      this.retVal(this._GeneralGetFailure);
      vRetVal = "";
      return vRetVal;
    }

    // We only handle 'cmi.XXXX' items....
    if (pValueName.substr(0, 4) != "cmi.") {
      return this.GetNavRequest(pValueName);
    }

    // Kill 'cmi.' from the front
    vDispName = pValueName.substr(4);
    // See if there is more than just the cmi.xxxx;
    //    if so, hack it off
    vDispIdx = vDispName.indexOf(".");
    vDispExtension = "";
    if (vDispIdx >= 0) {
      vDispExtension = vDispName.substr(vDispIdx + 1);
      vDispName = vDispName.substr(0, vDispIdx);
    }

    // Assume not error
    this.retVal(this._NoError);
    vRetValue = "";
    switch (vDispName) {
    case "_version":
      vRetVal = "1.0";
      break;

    case "comments_from_learner":
      vRetVal = "";
      break;

    case "comments_from_lms":
      vRetVal = "";
      break;

    case "completion_status":
      vRetVal = scormData.completion_status;
      break;

    case "completion_threshold":
      vRetVal = "";
      break;

    case "credit":
      vRetVal = "";
      break;

    case "entry":
      vRetVal = scormData.entry;
      break;

    case "exit":
      vRetVal = scormData.exit;
      break;

    case "interactions":
      vRetVal = "";
      break;

    case "launch_data":
      vRetVal = "";
      break;

    case "learner_id":
      vRetVal = scormData.learner_id;
      break;

    case "learner_name":
      vRetVal = scormData.learner_name;
      break;

    case "learner_preference":
      vRetVal = "";
      break;

    case "location":
      if (null == scormData.location) {
        this.retVal(this._DataModelElementValueNotInitialized);
        vRetVal = "";
      }
      else {
        vRetVal = scormData.location;
      }
      break;

    case "max_time_allowed":
      vRetVal = "";
      break;

    case "mode":
      vRetVal = scormData.mode;
      break;

    case "objectives":
      vRetVal = "";
      break;

    case "progress_measure":
      // Should be real number
      vRetVal = scormData.progress_measure;
      break;

    case "scaled_passing_score":
      vRetVal = scormData.scaled_passing_score;
      break;

    case "score":
      if ("scaled" == vDispExtension) {
        if (null == scormData.scaled_score) {
          this.retVal(
          this._DataModelElementValueNotInitialized);
          vRetVal = "";
        }
        else {
          vRetVal = scormData.scaled_score;
        }
      }
      else {
        vRetVal = "";
      }
      break;

    case "session_time":
      vRetVal = "";
      break;

    case "success_status":
      vRetVal = scormData.success_status;
      break;

    case "suspend_data":
      if (null == scormData.suspend_data) {
        this.retVal(this._DataModelElementValueNotInitialized);
        vRetVal = "";
      }
      else {
        vRetVal = scormData.suspend_data;
      }
      break;

    case "time_limit_action":
      vRetVal = "";
      break;

    case "total_time":
      vRetVal = "";
      break;

    default:
      vRetVal = "";
      this.retVal(this._UndefinedDataModelElement);
      break;
    }
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("GetValue", "GetValue('" + pValueName + "'): '" + vRetVal.toString() + "'" + vErrCode);
    }
    return vRetVal;
  },
  GetNavRequest: function (pValueName) {
    var vRetVal;
    vRetVal = "";
    this.retVal(this._NoError);
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("GetValue", "GetNavRequest [notimpl] ('" + pValueName + "'): '" + vRetVal.toString() + "'" + vErrCode);
    }
    return vRetVal;
  },
  onLocationChange: null,
  onSuspendDataChange: null,
  SetValue: function (pValueName, pValue) {
    var vRetVal;
    var vDispName;
    var vDispExtension;
    var vDispIdx;

    // Check for errors
    if ("" == this.status) {
      this.retVal(this._StoreDataBeforeInitialization);
      vRetVal = "false";
      return vRetVal;
    }
    if ("closed" == this.status) {
      this.retVal(this._StoreDataAfterTermination);
      vRetVal = "false";
      return vRetVal;
    }
    if ("" == pValueName) {
      this.retVal(this._GeneralSetFailure);
      vRetVal = "";
      return vRetVal;
    }

    // We only handle 'cmi.XXXX' items....
    if (pValueName.substr(0, 4) != "cmi.") {
      return this.SetNavRequest(pValueName, pValue);
    }

    // Kill 'cmi.' from the front
    vDispName = pValueName.substr(4);
    // See if there is more than just the cmi.xxxx;
    //    if so, hack it off
    vDispIdx = vDispName.indexOf(".");
    vDispExtension = "";
    if (vDispIdx >= 0) {
      vDispExtension = vDispName.substr(vDispIdx + 1);
      vDispName = vDispName.substr(0, vDispIdx);
    }

    // Assume success
    vRetVal = "true";
    this.retVal(this._NoError);
    switch (vDispName) {
    case "_version":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "comments_from_learner":
      // This is a multi-valued item
      break;

    case "comments_from_lms":
      // This is a multi-valued item
      break;

    case "completion_status":
      if (pValue != "completed" && pValue != "incomplete" && pValue != "not attempted") {
        this.retVal(this._DataModelElementTypeMismatch);
      }
      else {
        scormData.completion_status = pValue;
      }
      break;

    case "completion_threshold":
      this.retVal(this._DataModelElementIsReadOnly);
      break;

    case "credit":
      this.retVal(this._DataModelElementIsReadOnly);
      break;

    case "entry":
      this.retVal(this._DataModelElementIsReadOnly);
      break;

    case "exit":
      if (pValue != "time-out" && pValue != "suspend" && pValue != "logout" && pValue != "normal" && pValue != "") {
        this.retVal(this._DataModelElementTypeMismatch);
      }
      else {
        scormData.exit = pValue;
      }
      break;

    case "interactions":
      // This is a multi-valued item
      break;

    case "launch_data":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "learner_id":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "learner_name":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "learner_preference":
      // This is a multi-valued item
      break;

    case "location":
      scormData.location = pValue;
      if (null != scormData.onLocationChange) {
        scormData.onLocationChange(scormData);
      }
      break;

    case "max_time_allowed":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "mode":
      this.retVal(this._DataModelElementIsReadOnly);
      vRetVal = "false";
      break;

    case "objectives":
      // This is a multi-valued item
      break;

    case "progress_measure":
      break;

    case "scaled_passing_score":
      break;

    case "score":
    case "score.scaled":
      scormData.scaled_score = pValue;
      break;

    case "session_time":
      break;

    case "success_status":
      if (pValue != "passed" && pValue != "failed" && pValue != "unknown") {
        this.retVal(this._DataModelElementTypeMismatch);
        vRetVal = "false";
      }
      else {
        scormData.success_status = pValue;
        // Added by Vicsante Aseniero
        // To ensure that webinar will be completed if exam pass
        if ( pValue == "passed" ) {
          scormData.completion_status = "completed";
        }
      }
      break;

    case "suspend_data":
      scormData.suspend_data = pValue;
      if (null != scormData.onSuspendDataChange) {
        scormData.onSuspendDataChange(scormData);
      }
      break;

    case "time_limit_action":
      break;

    case "total_time":
      break;

    default:
      this.retVal(this._UndefinedDataModelElement);
      vRetVal = "false";
      break;
    }
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("SetValue", "SetValue(" + "'" + pValueName + "'" + ", " + "'" + pValue.toString() + "'" + "):" + vErrCode);
    }
    return vRetVal;
  },
  SetNavRequest: function (pValueName, pValue) {
    var vRetVal;
    vRetVal = "true";
    this.retVal(this._NoError);
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("SetValue", "SetNavRequest [notimpl] ('" + pValueName + "'" + ", '" + pValue + "'): '" + vRetVal.toString() + "'" + vErrCode);
    }
    return vRetVal;
  },
  Commit: function (pParam) {
    var vRetVal;

    this.retVal(this._NoError);
    vRetVal = "true";
    if ("" == this.status) {
      this.retVal(this._CommitBeforeInitialization);
      vRetVal = "false";
    }
    if ("closed" == this.status) {
      this.retVal(this._CommitAfterTermination);
      vRetVal = "false";
    }
    if (pParam != "") {
      this.retVal(this._GeneralArgumentError);
      vRetVal = "false";
    }
    if (dbWin) {
      var vErrCode;
      vErrCode = "";
      if (this.last_retVal) {
        vErrCode = "  err code " + this.last_retVal;
      }
      dbWin.out("Commit", "Commit(" + vRetVal + "):" + vErrCode);
    }

    // Transmit data to server
    Drupal.training.transmit();

    return vRetVal;
  },
  GetLastError: function () {
    return this.last_retVal.toString();
  },
  GetErrorString: function (pParam) {
    return "(error string for error code " + pParam.toString() + ")";
  },
  GetDiagnostic: function (pParam) {
    return "(diagnostic for error code " + pParam.toString() + ")";
  }
};
