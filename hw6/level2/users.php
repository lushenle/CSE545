<?php
if (!stristr($_SERVER['HTTP_REFERER'], "users.html")) {
  print "<pre>No users</pre>\n";
  exit(0);
}
if (isset($_GET['filter'])) {
  $filter = " | grep " . $_GET['filter'];
 } else {
  $filter = "";
 }
print "<pre>\n";
$command = "ps aux | grep -v USER | cut -f1 -d' ' | sort | uniq" . $filter;
system($command);
print "</pre>\n";
?>
