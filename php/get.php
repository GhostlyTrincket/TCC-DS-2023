<?php

	include("./connect.php");

	$mysql = connect();
	
	$select_last_row = "SELECT id, moisture FROM tbl_moisture ORDER BY id DESC LIMIT 1";
	$sel_last_row_result = $mysql->query($select_last_row);

	$last_row = $sel_last_row_result->fetch_assoc();

	$mysql->close();
	$sel_last_row_result->free();

	echo $last_row["moisture"];

	$mysql = NULL;
