  var firebaseConfig = {
    apiKey: "AIzaSyCtiBlFO9UFsjvp3V0TfHt1uK4ScAsQyTU",
    authDomain: "sensor2-4e7a3.firebaseapp.com",
    databaseURL: "https://sensor2-4e7a3.firebaseio.com",
    projectId: "sensor2-4e7a3",
    storageBucket: "sensor2-4e7a3.appspot.com",
    messagingSenderId: "228736456413",
    appId: "1:228736456413:web:e0934ffd9c2d50529dad34"
  };
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

/*
const puxarNovosDados = () => {
    var bigOne = document.getElementById('bigOne');
    var dbRef = firebase.database().ref("/3C:71:BF:9E:2A:50");
    dbRef.once('value', snap => {
        var ul = document.createElement('ul');
        snap.forEach(function (data) {
            var li1 = document.createElement('li');
            li1.innerText = "LDR : " + data.val().LDR;
            var li2 = document.createElement('li');
            li2.innerText = "Umidade : " + data.val().UmidadeBME;
            ul.appendChild(li1);
            ul.appendChild(li2);
            console.log("LDR : " + data.val().LDR);
            console.log("Umidade : " + data.val().UmidadeBME);
        })
        document.getElementById('inserirDados').appendChild(ul);
        //bigOne.innerText = snap.val();
    });
}

//Atualiza os cards a cada push
var dbRef = firebase.database().ref("/3C:71:BF:9E:2A:50");
dbRef.on('child_added', function (snapshot) {
    //console.log(snapshot.val());
    var cardLDR = document.getElementById('cardLDR');
    var cardUmidade = document.getElementById('cardUmidade');
    var cardPressao = document.getElementById('cardPressao');
    var cardTemperatura = document.getElementById('cardTemperatura');
    cardLDR.innerText = snapshot.val().LDR;
    cardUmidade.innerText = snapshot.val().UmidadeBME + " %";
    cardPressao.innerText = snapshot.val().PressaoBME + " hPa"
    cardTemperatura.innerText = snapshot.val().TempBME + " °C";
})
*/




