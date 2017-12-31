(function ($) {
    Drupal.behaviors = Drupal.behaviors || {};

    Drupal.behaviors.indices_delete_confirm = {
        attach: function (context, settings) {
            $(document).on('click', '#edit-build-repository', function (e) {
                if (confirm("Warning: this will copy the registered XMLs to the Galaxy tool repository. " +
                        "Existing XMLs will be overwritten with the updated XMLs. Are you sure you want to continue?")) {
                }
                else {
                    e.preventDefault();
                }
            });
        }
    }
})(jQuery)