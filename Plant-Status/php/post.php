<?php
	include("./connect.php");

	$mysql = connect();
	$insert = "INSERT INTO umidade_tbl(umidade) VALUES(".$_POST['umidade'].")";

	if(empty($_POST["umidade"])) {
		echo "error";
	} else {
		if(!$mysql->query($insert)) {
			echo "houve um erro durante a inserção da data!";
		}

		echo "Inserido com sucesso!";
	}

	$mysql->close();

	$mysql = NULL;
