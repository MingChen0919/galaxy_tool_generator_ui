(function ($) {
    Drupal.behaviors = Drupal.behaviors || {};

    Drupal.behaviors.indices_delete_confirm = {
        attach: function (context, settings) {
            $(document).on('click', '#edit-from-galaxy-to-gtg', function (e) {
                if (confirm("Warning: this will empty the galaxy tool repository built with GTG and replace it with contents " +
                        "from the specified tool repository from a running Galaxy instance. " +
                        "Are you sure you want to continue?")) {
                }
                else {
                    e.preventDefault();
                }
            });
        }
    }
})(jQuery)