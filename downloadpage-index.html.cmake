<!DOCTYPE html>
<html>
<head>
<title>ARSnovaDesktop - Download</title>
<meta charset="UTF-8" />
<meta name="description" content="ARSnovaDesktop - Download" />
<meta name="author" content="ARSnovaDesktop - Download" />
<link type="text/css" href="//fonts.googleapis.com/css?family=Roboto" rel="stylesheet" />
<link type="text/css" href="//fonts.googleapis.com/css?family=Open+Sans:300,400,600" rel="stylesheet" />
<link type="text/css" rel="stylesheet" href="style.css" />
<link type="text/css" rel="stylesheet" href="//ajax.googleapis.com/ajax/libs/dojo/1.9.1/dijit/themes/tundra/tundra.css" />
<script src="//ajax.googleapis.com/ajax/libs/dojo/1.9.1/dojo/dojo.js"></script>
</head>
<body class="tundra">
	<header>
		<div class="automargin"><img src="arsnova.png" alt="ARSnova" /></div>
	</header>
	<div class="automargin">
		<nav id="topmenu">
			<ul>
				<li><a class="menu-link" href="http://blog.mni.thm.de/arsnova/">Aktuelles zu ARSnova</a></li>
				<li><a class="menu-link" href="#infotext">Hinweise zur Verwendung</a></li>
				<li><a class="menu-link" href="#downloadselector">Download</a></li>
			</ul>
		</nav>
	</div>
	<div id="content">
		<div class="intro">
		  <img src="screen.jpg" alt="ARSnova" />
		  <h2>ARSnova Overlay - damit zeigen Sie mehr</h2>
		  <p>
		    Wenn Sie Ihre Präsentationen durch ARSnova unterstützen möchten oder einfach nur zeigen wollen, wie Ihr Vortrag ankommt
		    - ARSnova Overlay unterstützt Sie dabei.
		  </p>
		  <a class="bold-link" href="http://blog.mni.thm.de/arsnova/">Aktuelles zu ARSnova</a>
		</div>
		<article id="infotext">
			<h2>Nutzen Sie ARSnova Overlay für Ihre Präsentationen</h2>
			<p>
				ARSnova Overlay bietet auf einfache Art die Möglichkeit, das Live-Feedback in die Beamer-Präsentation einzubinden.
				Als Dozent/in können Sie sich ganz auf Ihre Präsentation konzentrieren und sehen auf den Folien, ob das Publikum Ihren Vortrag folgen kann.
			</p>
			<p>
				Wählen Sie zwischen verschiedenen Darstellungen Balken, ARSnova-Icon oder Smiley-Emoticons oder generieren Sie einen QR-Code Ihrer ARSnova-Session und ziegen diese im Vollbildmodus an.
				Mit dem QR-Code gelangt man direkt auf die Feedback-Seite von ARSnova.
			</p>
			<p>
				Für die Verwendung mit Apple Keynote muss es anderen Anwendungen möglich sein, den Bildschirm mit zu nutzen. <br/><span id="help001" class="help">Mehr erfahren</span>
			</p>
			<p>
				Erleben Sie es selbst und wählen Sie <b>ARSnova Overlay</b> für Ihre Plattform.
			</p>
		</article>
	</div>
	<h2>Download der aktuellen Version @VERSION_SHORT@</h2>
	<div id="downloadselector">
		<a id="win" href="http://download.mni.thm.de/arsnova/arsnovaoverlay-@VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@-win32.exe">Windows</a>
		<a id="osx" href="http://download.mni.thm.de/arsnova/arsnovaoverlay-@VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@-Darwin.dmg">Mac OS X</a>
		<a id="deb" href="http://download.mni.thm.de/arsnova/arsnovaoverlay_@VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@_amd64.deb">Linux DEB</a>
		<a id="rpm" href="http://download.mni.thm.de/arsnova/arsnovaoverlay-@VERSION_MAJOR@.@VERSION_MINOR@.@VERSION_PATCH@.x86_64.rpm">Linux RPM</a>
		<div id="others">
			Ältere Versionen finden Sie <a href="http://download.mni.thm.de/arsnova">hier</a>
		</div>
	</div>
	<script type="text/javascript">
		dojo.require('dijit.Tooltip');
		
		dojo.ready(
			function() {
				new dijit.Tooltip({
					connectId: ['help001'],
					label: '<p>Verwenden Sie die markierte Einstellung für Apple Keynote. Sie finden die Einstellungen im Menü direkt unter dem Menüpunkt <b>Keynote</b>.</p><img src="keynote.png" alt="Keynote Settings" />',
					position: ['after']
				});
				new dijit.Tooltip({
					connectId: ['win'],
					label: 'Installationspaket für alle Windows-Versionen ab Windows XP.',
					position: ['below']
				});
				new dijit.Tooltip({
					connectId: ['osx'],
					label: 'Installationspaket für Mac OS X ab Version 10.7 (Lion).',
					position: ['below']
				});
				new dijit.Tooltip({
					connectId: ['deb'],
					label: 'Verwenden Sie dieses Paket für Debian-basierte Distributionen wie <b>Debian, (K)Ubuntu</b> oder <b>elementaryOS</b>',
					position: ['below']
				});
				new dijit.Tooltip({
					connectId: ['rpm'],
					label: 'Verwenden Sie dieses Paket für Distributionen die RPM unterstützen wie <b>Fedora</b> oder <b>OpenSuse</b></b>',
					position: ['below']
				});
			}		
		);
	</script>
</body>
</html>
