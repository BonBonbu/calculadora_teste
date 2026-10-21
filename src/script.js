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
async function calcular() {
    if (expressao.trim() === "") {
        return;
    }

    try {
        console.log("Expressão enviada ao C++:", expressao);

        const resultado = await window.calculadora.calcular(expressao);

        expressao = resultado;
        document.getElementById("tela").value = resultado;
    } catch (erro) {
        document.getElementById("tela").value = "Erro";
        console.error("Erro ao calcular:", erro);
        console.error("Expressão que causou o erro:", expressao);
    }
}
