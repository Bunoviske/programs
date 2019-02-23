
const jwt = require("jsonwebtoken");

$(document).ready(function () {
    
    console.log("Iniciando BI");

    var version = document.getElementById("version");
    version.innerHTML = "1.0";

    /********************public embedded ******************/

    //document.getElementById("bi").src = "http://localhost:3000/public/dashboard/70121dcb-1521-4549-a9ba-99a16ec0dce5/#refresh=60&fullscreen&night";


    /********************application embedded ******************/


    var METABASE_SITE_URL = "http://localhost:3000";
    var METABASE_SECRET_KEY = "ffa63c02e613e0a4666163bdbbb454b33b3cf5a7632e9086cbe45137a533d391";

    var academia = "AFC";

    var payload = {
        resource: { dashboard: 33 },
        params: {
            //"academia": academia
        }
    };

    var token = jwt.sign(payload, METABASE_SECRET_KEY);

    document.getElementById("bi").src = METABASE_SITE_URL + "/embed/dashboard/" + token + "#theme=night&bordered=true&titled=true";

});


