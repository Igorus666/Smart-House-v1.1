function AlteraEstadoDisplay(){
    var estado = document.getElementById("estado").innerHTML;
    if(estado === "1"){
        document.getElementById("estado").innerHTML="0";
        document.getElementById("rele").innerHTML="<div class='rele_desligado'></div>";
        document.getElementById("botao").innerHTML="<a href='/?ligar' class='botao'>Ligar Display</a>";
    } else {
        document.getElementById("estado").innerHTML="1";
        document.getElementById("rele").innerHTML="<div class='rele_ligado'></div>";
        document.getElementById("botao").innerHTML="<a href='/?desligar' class='botao'>Desligar Display</a>";
    }
}