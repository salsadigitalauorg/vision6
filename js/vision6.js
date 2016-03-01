/**
 * Javascript for donate entity module.
 */

(function ($, Drupal, window, document, undefined) {
    $(document).ready(function(){
        $('#edit-field-vis6-new-published-as-synd-und').on('change', function() {
            $('input[name="field_vis6_published_as_synd[und]"]').prop('checked', $(this).prop("checked"));
        });
        $('#edit-field-vis6-new-syndication-type-und').on('change', function() {
            $('select[name="field_vis6_syndication_type[und]"]').val($(this).val());
        });
        $('#edit-field-vis6-new-email-type-und').on('change', function() {
            $('select[name="field_vis6_email_type[und]"]').val($(this).val());
        });
        $('#edit-field-vis6-new-type-und').on('change', function() {
            $('select[name="field_vis6_type[und]"]').val($(this).val());
        });
        $('#edit-field-vis6-new-contact-list-id-und').on('change', function() {
            $('select[name="field_vis6_contact_list_id[und]"]').val($(this).val());
        });
        $('#edit-field-vis6-new-inc-body-synd-und').on('change', function() {
            $('input[name="field_vis6_inc_body_synd[und]"]').prop('checked', $(this).prop("checked"));
        });
    });
})(jQuery, Drupal, this, this.document);
