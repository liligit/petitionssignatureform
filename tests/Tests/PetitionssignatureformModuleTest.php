<?php

/**
 * @file
 * Contains PetitionssignatureformModuleTest.
 */

require_once dirname(__FILE__) . '/../../petitionssignatureform.module';

/**
 * Tests the functions in petitionssignatureform.module.
 *
 * @todo Test that the signature form constructor hides the Petition ID field
 *   and supplies a default value if a petition ID is supplied.
 * @todo Test that signature form constructor shows the Petition ID field and
 *   does not supply a default value if a petition ID is *not* supplied.
 */
class PetitionssignatureformModuleTest extends PHPUnit_Framework_TestCase {

  /**
   * Tests that the signature form constructor rejects an invalid petition ID.
   *
   * @dataProvider providerSignatureFormRejectsInvalidPetitionId
   *
   * @expectedException InvalidArgumentException
   *
   * @param mixed $petition_id
   *   An invalid petition ID value.
   *
   * @see petitionssignatureform_signature_form()
   */
  public function testSignatureFormRejectsInvalidPetitionId($petition_id) {
    $form_state = NULL;
    petitionssignatureform_signature_form(NULL, $form_state, $petition_id);
  }

  /**
   * Data provider for testSignatureFormRejectsInvalidPetitionId().
   *
   * @see testSignatureFormRejectsInvalidPetitionId()
   */
  public function providerSignatureFormRejectsInvalidPetitionId() {
    $tests[] = array(array());
    $tests[] = array(0);
    $tests[] = array('');

    return $tests;
  }

}
