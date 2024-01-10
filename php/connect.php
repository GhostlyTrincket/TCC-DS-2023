<?php

function connect_to(string $db_name, string $password, string $user, string $host = "localhost", int $port) {
	$mysql = mysqli_connect($host, $user, $password, $db_name, $port);
	
	if($mysql->connect_errno) {
		echo "Could not connect to DB ".$db_name."!\n";
		exit(1);
	}

	return $mysql;
}
