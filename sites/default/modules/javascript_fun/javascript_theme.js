/*(function($) {
  // Declare a theme function
  Drupal.theme.prototype.hello = function(text) {
    return Drupal.t('Hello @city', {'@city' : text}); 
  }
  // Define a behavior for our module:
  Drupal.behaviors.helloWorld = {
    
    // Attach function: Runs when new content is added to the DOM.
    attach: function(context, settings) {
      $('#ajax_markup_div', context).once('ajax_markup_div_attach', function() {
        alert(Drupal.theme('hello', 'Randers') + ' ' + context + ' ' + settings);
        alert(Drupal.settings.helloWorld.message);
        alert('This alert only runs ones per AJAX request');
      });
    },
    
    
    // Detach function: Runs when content is removed from the DOM.
    detach: function (context, settings, trigger) {      
      $('#ajax_markup_div', context).once('ajax_markup_div_detach', function() {
        alert('This is a detach function');
        console.log(trigger);
      }); 
    }
    
  };
  
  $(document).ready(function() {
    alert('This alert only runs ones per full page request');
  });
  
})(jQuery);*/


