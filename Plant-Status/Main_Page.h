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
			<p id="paragrafo">Umidade: </p>
		</main>

   <script type="text/javascript">
      const xml_http = new XMLHttpRequest();

      xml_http.open("GET", "/xml");
      xml_http.send();

      // when the page finishes loading, do this:
      xml_http.onload = () => {
        if(xml_http.readyState === xml_http.DONE || xml_http.status === 200) {
          const moisture = Number(xml_http.responseXML.firstElementChild.children[0].innerHTML);

        // appends moisture_value to the tag with the correspondent ID
          document.getElementById("paragrafo").innerHTML += moisture;
        }
      }

      console.log("Got XMl!");
   </script>

	</body>

</html>
)=====";
