<?php
$cache_expire = 60*60*24*265;
header('Pragma: public');
header('Cache-Control: max-age=' . $cache_expire);
header('Expires: ' . gmdate('D, d M Y H:i:s', time() + $cache_expire) . ' GMT');
?>
<script src="//connect.facebook.net/da_DK/all/debug.js"></script>