var system = require('system');
var args = system.args;

var timeout=3200;
if (args.length > 4) {
  timeout=args[4];
}

if (args.length < 2) {
  console.log('Vnesi naslov spletne strani, ki jo želiš slikati :)');
   phantom.exit();
} else {

var webPage = require('webpage');
var page = webPage.create();

if (args.length > 3) {
  var res=args[3].split("x");
  page.viewportSize = { width: res[0], height: res[1] };
}else{
  page.viewportSize = { width: 1920, height: 1080 };
}

page.open( args[1], function start(status) {
  
  
  
  window.setTimeout(function () {
    if (args.length == 2) {
      page.render('output.pdf', {format: 'pdf'});
    }else{
      page.render( args[2], {format: 'pdf'});
    }
            phantom.exit();
        }, timeout);
});

}
