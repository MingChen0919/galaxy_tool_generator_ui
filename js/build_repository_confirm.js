(function ($) {
    Drupal.behaviors = Drupal.behaviors || {};

    Drupal.behaviors.indices_delete_confirm = {
        attach: function (context, settings) {
            $(document).on('click', '#edit-build-repository', function (e) {
                if (confirm("Warning: you can not undo this step!")) {
                }
                else {
                    e.preventDefault();
                }
            });
        }
    }
})(jQuery)