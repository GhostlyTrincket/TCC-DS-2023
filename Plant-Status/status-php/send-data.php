<?php
	$db_name = "teste_db";
	$db_pass = "ghostlyTr1nk37";
	$db_user = "root";
	$db_host = "localhost";

	$mysql_conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
	$sql_op = "INSERT INTO umidade_tbl(umidade) VALUES(".$_POST['umidade'].")";


	
	if(empty($_POST["umidade"])) {
		echo "error";
	} else {
		if(!$mysql_conn->query($sql_op)) {
			echo "houve um erro durante a inserção da data!";
		}

		echo "Inserido com sucesso!";
	}

	mysqli_close($mysql_conn);
