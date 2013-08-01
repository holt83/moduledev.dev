
(function($) {
  // Declare a theme function
  Drupal.theme.prototype.hello = function(text) {
    return Drupal.t('Hello @city', {'@city' : text}); 
  }
  // Attach a behavior:
  Drupal.behaviors.helloWorld = {
    
    attach: function(context, settings) {
      
      $('#ajax_markup_div', context).once('ajax_markup_div', function() {
        alert(Drupal.theme('hello', 'Randers') + ' ' + context + ' ' + settings);
        alert(Drupal.settings.helloWorld.message);
        alert('Attach function for helloWorld behavior is done!');
        alert('This alert only runs ones per AJAX request');
      }); 
    }
    
  };
  
  $(document).ready(function() {
    alert('This alert only runs ones per full page request');
  });
  
})(jQuery);


