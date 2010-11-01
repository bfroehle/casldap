<?php
// $Id$

/**
 * Provides settings pages.
 */
function casldap_admin_settings() {

  $form['ldap'] = array(
    '#type' => 'fieldset',
    '#title' => t('LDAP server settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['ldap']['casldap_ldap_server'] = array(
    '#type' => 'textfield',
    '#title' => t('LDAP server'),
    '#default_value' => variable_get('casldap_ldap_server', ''),
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('The domain name or IP address of your LDAP Server.'),
  );
  $form['ldap']['casldap_ldap_port'] = array(
    '#type' => 'textfield',
    '#title' => t('LDAP port'),
    '#default_value' => variable_get('casldap_ldap_port', '389'),
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The TCP/IP port on the above server which accepts LDAP connections. Must be an integer. 389 is the standard LDAP port.'),
  );

  $form['ldap']['casldap_ldap_basedn'] = array(
    '#type' => 'textfield',
    '#title' => t('Base DN'),
    '#default_value' => variable_get('casldap_ldap_basedn', ''),
    '#size' => 50,
    '#description' => t('Base DN for users.'),
  );

  $form['ldap']['casldap_ldap_user_attribute'] = array(
    '#type' => 'textfield',
    '#title' => t('Username attribute'),
    '#default_value' => variable_get('casldap_ldap_user_attribute', 'uid'),
    '#size' => 30,
    '#description' => t("The attribute that holds the users' CAS login name."),
  );

  module_load_include('inc', 'field_ui', 'field_ui.admin');  

  $instances = field_info_instances('user', 'user');

  $casldap_relations = variable_get('casldap_relations','');
  
  $form['relations'] = array(
    '#type' => 'fieldset',
    '#title' => t('LDAP server settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['relations'] = array(
    '#type' => 'fieldset',
    '#title' => t('LDAP attribute mappings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['relations']['help'] = array(
    '#markup' => t('Which LDAP attributes should be used to populate each <a href="@url">user field</a> upon account creation?  Only text fields are eligible to be populated.  Entries left blank will not be populated.', array('@url' => url('admin/config/people/accounts/fields'))),
  );
  
  $form['relations']['casldap_relations'] = array(
    '#tree' => TRUE,
    '#type' => null,
  );

  if (variable_get('cas_authmap',0) == 0) {
    // Only allow changing the name of user if we're using CAS_AUTHMAP_EXTERNAL
    $form['relations']['casldap_relations']['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#default_value' => isset($casldap_relations['name']) ? $casldap_relations['name'] : '',
      '#size' => 50,
      '#description' => t('The LDAP attribute containing the account username.'),
    );
  }

  $form['relations']['casldap_relations']['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => isset($casldap_relations['mail']) ? $casldap_relations['mail'] : '',
    '#size' => 50,
    '#description' => t('The LDAP attribute containing the account e-mail address.'),
  );
  
  foreach ($instances as $name => $instance) {
    $field = field_info_field($instance['field_name']);
    if($field['type'] == 'text') {
      $form['relations']['casldap_relations'][$name] = array(
        '#type' => 'textfield',
        '#title' => check_plain($instance['label']),
        '#default_value' => isset($casldap_relations[$name]) ? $casldap_relations[$name] : '',
        '#size' => 50,
        '#description' => 'The LDAP attribute containing the account field with name ' . $instance['field_name'] . '.',
      );
    }
  }
  
  return system_settings_form($form);
}
