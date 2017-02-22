<div class="left">
    <div class="users">
        <?php if (isset($fields['name'])) print $fields['name']->content; ?>        
    </div>
    <div class="myaccount">    
        <?php if (isset($fields['nothing_1'])) print $fields['nothing_1']->content; ?> | 
        <?php if (isset($fields['nothing'])) print $fields['nothing']->content; ?>
        
    </div>

</div>
<div class="right"><?php if (isset($fields['picture'])) print $fields['picture']->content; ?></div>
    