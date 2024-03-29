const char MAIN_PAGE[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="pt-BR">

	<head>
		<title>Teste</title>
		<meta charset="UTF-8" />
		<meta name="viewport" content="width=device-width,initial-scale=1.0" />
	</head>
	<body onload="process()">

		<header>
			<h1>Plant Status: Dashboard</h1>
		</header>

		<main>
			<p>Umidade da terra (%): <span id="percentage-moisture"></span></p>
			<p>Umidade da terra (decimal): <span id="moisture-decimal"></span></p>
		</main>

		<script type="text/javascript">
			const xml_http = new XMLHttpRequest();
			const time_delay = 1000;
			const time_out = time_delay / 2;

			xml_http.open("GET", "/xml");

			setInterval(update_moisture, time_delay);

			function update_moisture() {
				const update_request = new XMLHttpRequest();
				const xml_response = xml_http.responseXML.getElementsByTagName("Moisture")[0].innerHTML;

				update_request.onload = () => {
					if(update_request.readyState == 4 && update_request.status == 200) {
						const processed_moisture = Number(update_request.responseText);

						document.getElementById("percentage-moisture").innerHTML = processed_moisture + '%';
					}
				}

				update_request.open("PUT", "/update_moisture?m="+Number(xml_response), true);
				update_request.send();
			}

			function respond() {
				const response = xml_http.responseXML;
				const moisture_value = response.getElementsByTagName("Moisture")[0].innerHTML;

				document.getElementById("moisture-decimal").innerHTML = moisture_value;
			}

			function process() {
				if(xml_http.readyState == 0 || xml_http.readyState == 4) {
					xml_http.open("PUT", "/xml", true);

					xml_http.onreadystatechange = respond;

					xml_http.send(null);
				}

				setTimeout("process()", time_out);
			}

			xml_http.send();
		</script>
	</body>
</html>
)=====";
