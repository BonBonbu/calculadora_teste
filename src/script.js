let expressao = "";

function adicionar(valor) {
    expressao += valor;
    document.getElementById("tela").value = expressao;
}

function apagar() {
    expressao = expressao.slice(0, -1);
    document.getElementById("tela").value = expressao;
}

function limpar() {
    expressao = "";
    document.getElementById("tela").value = "";
}