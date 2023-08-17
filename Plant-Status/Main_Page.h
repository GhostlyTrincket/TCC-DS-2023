const char MAIN_PAGE[] PROGMEM = R"=====(
// prepare to see a lot of bullshit here! i funcking hate Javascript

<!DOCTYPE html>
<html lang="pt-BR">

	<head>
		<title>Teste</title>
		<meta charset="UTF-8" />
		<meta name="viewport" content="width=device-width,initial-scale=1.0" />
	</head>

  <style>

.paragrafo { display: none }

  </style>

	<body onload="process()">

		<header>
			<h1>Plant Status: Dashboard</h1>
		</header>

		<main>
			<p class="paragrafo">Umidade da terra (%): <span id="percentage-moisture"></span></p>
			<p class="paragrafo">Umidade da terra (decimal): <span id="moisture-decimal"></span></p>

			<button onclick="update_moisture()">Analizar umidade</button>
		</main>

		<script type="text/javascript">
			const xml_http = new XMLHttpRequest();
			const paragrafo = document.getElementsByClassName("paragrafo"); // returns a array of paragraths

			xml_http.open("GET", "/xml");

			function update_moisture() {
				const update_request = new XMLHttpRequest();
				const xml_response = xml_http.responseXML.getElementsByTagName("Moisture")[0].innerHTML;

				update_request.onload = () => {
					if(update_request.readyState == 4 && update_request.status == 200) {
						paragrafo[0].style.display = "block";
						paragrafo[1].style.display = "block";

						const new_moisture = Number(update_request.responseText);
						const moisture_percentege = getPercentage(new_moisture);

						document.getElementById("percentage-moisture").innerHTML = moisture_percentege + '%';
					}
				}

				update_request.open("PUT", "/update_moisture?value="+Number(xml_response), true));
				update_request.send();
			}

			function get_percentage(moisture_to_parse) {
				if(moisture_to_parse >= 100) {
					  return 100;
				} else if (moisture_to_parse <= 0) {
					  return 0;
				}

				return moisture_to_parse;
			}

			function respond() {
				const response = xml_http.responseXML;
				const moisture_value = response.getElementsByTagName("Moisture")[0].innerHTML;

				if(response === null) {
					// just don't do nothing
				} else {
				  document.getElementById("moisture-decimal").innerHTML = moisture_value;
				}
			 }

			function process() {
				//alter `time_out`'s to a bigger value, if the page get big.
				const time_out = 200;

				if(xml_http.readyState == 0 || xml_http.readyState == 4) {
					xml_http.open("PUT", "xml", true);

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
