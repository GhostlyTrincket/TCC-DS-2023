<?php
	include("./connect.php");

	$mysql = connect();

	$sql_op = "INSERT INTO tbl_moisture(moisture) VALUES(".$_POST["umidade"].")";

	if(empty($_POST["umidade"])) {
		echo "error";
	} else {
		if(!$mysql->query($sql_op)) {
			echo "houve um erro durante a inserção da data!";
		}

		echo "Inserido com sucesso!";
	}

	$mysql->close();
	$mysql = NULL;
