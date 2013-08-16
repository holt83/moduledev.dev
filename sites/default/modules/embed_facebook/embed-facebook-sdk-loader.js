window.fbAsyncInit = function() {
  FB.init({
    appId: Drupal.settings.embedFacebook.appId,
    channelUrl: Drupal.settings.embedFacebook.channelUrl,
    status: true,
    xfbml: true
  });
};
(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s);js.id = id;
  js.src = "//connect.facebook.net/da_DK/all/debug.js";
  fjs.parentNode.insertBefore(js, fjs);
}(document, "script", "facebook-jssdk"));