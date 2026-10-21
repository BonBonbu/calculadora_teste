
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('calculadora', {
    calcular: (expressao) => ipcRenderer.invoke('calcular', expressao)
});
