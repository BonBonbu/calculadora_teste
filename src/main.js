const { app, BrowserWindow, ipcMain } = require('electron');
const { spawn } = require('child_process');
const path = require('path');

function criarJanela() {
    const janela = new BrowserWindow({
        width: 450,
        height: 700,
        resizable: true,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            nodeIntegration: false
        }
    });

    janela.loadFile(path.join(__dirname, 'calculadora.html'));
}

ipcMain.handle('calcular', async (evento, expressao) => {
    return new Promise((resolve, reject) => {
        const programa = spawn(
            path.join(__dirname, 'calculadora.exe')
        );

        let saida = '';
        let erro = '';

        programa.stdout.setEncoding('utf8');
        programa.stderr.setEncoding('utf8');

        programa.stdout.on('data', (dados) => {
            saida += dados;
        });

        programa.stderr.on('data', (dados) => {
            erro += dados;
        });

        programa.on('error', () => {
            reject(new Error('Não foi possível executar o programa C++.'));
        });

        programa.on('close', (codigo) => {
            if (codigo !== 0) {
                reject(new Error(erro || 'Expressão inválida.'));
                return;
            }

            const resultado = saida.match(/Resultado:\s*(.+)/);

            if (resultado) {
                resolve(resultado[1].trim());
            } else {
                reject(new Error('Não foi possível ler o resultado.'));
            }
        });

        programa.stdin.end(expressao + '\n');
    });
});

app.whenReady().then(criarJanela);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});
