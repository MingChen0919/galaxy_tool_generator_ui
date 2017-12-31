(function ($) {
    Drupal.behaviors = Drupal.behaviors || {};

    Drupal.behaviors.indices_delete_confirm = {
        attach: function (context, settings) {
            $(document).on('click', '#edit-remove-xmls--3', function (e) {
                if (confirm("Warning: this can not be undone. Are you sure you want to continue?")) {
                }
                else {
                    e.preventDefault();
                }
            });
        }
    }
})(jQuery)