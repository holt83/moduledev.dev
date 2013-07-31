(function($) {
  // Declare a theme function
  Drupal.theme.prototype.hello = function(text) {
    return Drupal.t('Hello @city', {'@city' : text}); 
  }
  // Attach a behavior:
  Drupal.behaviors.helloWorld = {
    attach: function(context, settings) {
      alert(Drupal.theme('hello', 'Randers') + ' ' + context + ' ' + settings);
    }
  };
})(jQuery);


