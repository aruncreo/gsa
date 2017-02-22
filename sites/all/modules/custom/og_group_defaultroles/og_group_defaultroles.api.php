<?php

/**
 * @file
 * Hooks provided by the Organic Groups Default Roles module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Add conditions to evalulate for default role assignment.
 */
function og_group_defaultroles_conditions() {
  return array(
    'function_name' => 'Function human-readable name',
  );
}

/**
 * @} End of "addtogroup hooks".
 */