(function ($) {
    Drupal.behaviors = Drupal.behaviors || {};

    Drupal.behaviors.indices_delete_confirm = {
        attach: function (context, settings) {
            $(document).on('click', '#edit-from-gtg-to-galaxy', function (e) {
                if (confirm("Warning: this will empty the specified tool repository within a connected running Galaxy instance " +
                        "and replace it with the galaxy tool repository built with the GTG. " +
                        "Are you sure you want to continue?")) {
                }
                else {
                    e.preventDefault();
                }
            });
        }
    }
})(jQuery)