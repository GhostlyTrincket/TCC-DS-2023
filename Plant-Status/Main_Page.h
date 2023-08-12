const char MAIN_PAGE[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="pt-BR">

	<head>
		<title>Teste</title>
		<meta charset="UTF-8" />
		<meta name="viewport" content="width=device-width,initial-scale=1.0" />
	</head>

	<body>

		<header>
			<h1>Hello World!</h1>
		</header>

		<main>
			<p>Umidade: <span id="moisture"></span></p>
			<button onclick="update_moisture()">Clique em mim para iniciar</button>
		</main>

		<script type="text/javascript">
			const xml_http = new XMLHttpRequest();

			xml_http.open("GET", "/xml");

			function update_moisture() {
				const update_request = new XMLHttpRequest();
				const xml_response = xml_http.responseXML;

				update_request.onreadystatechange = () => {
					if(update_request.readyState == 4 && update_request.status == 200) {
						const real_time_moisture = Number(update_request.responseText);

						document.getElementById("moisture").innerHTML = real_time_moisture;
					}
				}

				update_request.open("PUT", "/update_moisture?value="+Number(xml_response.getElementsByTagName("Moisture")[0].innerHTML, true))
				update_request.send();
			}

			function respond_to_process() {
        // const request = new XMLHttpRequest();

        // request.open("GET", "/xml");

				const bad_soil = 1230;
				const good_soil = 2460;
				const very_good_soil = 3690;

				const xml_response = xml_http.responseXML;
				const xml_document = Number(xml_response.getElementsByTagName("Moisture"));

				let moisture = xml_document[0].innerHTML;

				console.log(moisture);

        if(moisture <= 0 && moisture <= bad_soil) {
          console.log("the soil is bad");
        } else if(moisture > bad_soil && moisture <= good_soil) {
          console.log("the soil is good");
        } else if(moisture > good_soil && moisture <= very_good_soil) {
          console.log("the soil is perfect.");
        }

        // request.send(null);
			}

			function process() {
				//alter `time_out`'s to a bigger value, if the page get big.
				const time_out = 100;

				if(xml_http.readyState == 0 || xml_http.readyState == 4) {
					xml_http.open("PUT", "/xml", true);

					xml_http.onreadystatechange = respond_to_process;

					xml_http.send(null);
				}

				setTimeout("process()", time_out);
			}

			xml_http.send();

		</script>

	</body>
</html>

)=====";
