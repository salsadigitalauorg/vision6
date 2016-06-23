<?php
/**
 * @file
 * Vision6 subscribe class.
 */

/**
 * Vision6SubscribeFormControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */
interface Vision6SubscribeFormControllerInterface extends DrupalEntityControllerInterface {

  /**
   * Creates an entity.
   */
  public function create();

  /**
   * Saves an entity.
   *
   * @param object $entity
   *   The entity to save.
   */
  public function save($entity);

  /**
   * Deletes an entity.
   *
   * @param object $entity
   *   The entity to delete.
   */
  public function delete($entity);

}

/**
 * Vision6SubscribeFormController extends DrupalDefaultEntityController.
 *
 * Our subclass of DrupalDefaultEntityController lets us add a few
 * important create, update, and delete methods.
 */
class Vision6SubscribeFormController extends DrupalDefaultEntityController implements Vision6SubscribeFormControllerInterface {

  /**
   * Creates and return a new vision6_subscribe entity.
   */
  public function create() {
    $entity = new stdClass();
    $entity->type = 'vision6_subscribe';
    $entity->vsid = 0;
    $entity->listid = 0;
    $entity->title = '';
    $entity->firstname = '';
    $entity->lastname = '';
    $entity->email = '';
    $entity->approval = '';
    $entity->approval_format = filter_default_format();
    $entity->body = '';
    $entity->body_format = filter_default_format();
    $entity->created = time();
    $entity->bundle_type = 'vision6_subscribe_bundle';
    return $entity;
  }

  /**
   * Saves the custom fields using drupal_write_record().
   */
  public function save($entity) {
    // If our entity has no vsid, then we need to give it a
    // time of creation.
    if (empty($entity->vsid)) {
      $entity->created = time();
    }
    // Invoke hook_entity_presave().
    module_invoke_all('entity_presave', $entity, 'vision6_subscribe');
    // The 'primary_keys' argument determines whether this will be an insert
    // or an update. So if the entity already has an ID, we'll specify
    // vsid as the key.
    $primary_keys = $entity->vsid ? 'vsid' : array();
    // Write out the entity record.
    drupal_write_record('vision6_subscribe', $entity, $primary_keys);
    // We're going to invoke either hook_entity_update() or
    // hook_entity_insert(), depending on whether or not this is a
    // new entity. We'll just store the name of hook_entity_insert()
    // and change it if we need to.
    $invocation = 'entity_insert';
    // Now we need to either insert or update the fields which are
    // attached to this entity. We use the same primary_keys logic
    // to determine whether to update or insert, and which hook we
    // need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('vision6_subscribe', $entity);
    }
    else {
      field_attach_update('vision6_subscribe', $entity);
      $invocation = 'entity_update';
    }
    // Invoke either hook_entity_update() or hook_entity_insert().
    module_invoke_all($invocation, $entity, 'vision6_subscribe');
    return $entity;
  }

  /**
   * Deletes a single entity.
   *
   * Really a convenience function for deleteMultiple().
   */
  public function delete($entity) {
    $this->deleteMultiple(array($entity));
  }

  /**
   * Deletes one or more vision6_subscribe entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param array $entities
   *   An array of entity IDs or a single numeric ID.
   *
   * @throws Exception
   */
  public function deleteMultiple($entities) {
    /* @var $entities type hinting */
    $vsids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          // Invoke hook_entity_delete().
          module_invoke_all('entity_delete', $entity, 'vision6_subscribe');
          field_attach_delete('vision6_subscribe', $entity);
          $vsids[] = $entity->vsid;
        }
        db_delete('vision6_subscribe')
          ->condition('vsid', $vsids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('vision6_subscribe', $e);
        throw $e;
      }
    }
  }

}
