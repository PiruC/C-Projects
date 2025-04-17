const { app, BrowserWindow, ipcMain } = require("electron")
const path = require("path")
const fs = require("fs")

let mainWindow

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1200,
    height: 800,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
    },
  })

  mainWindow.loadFile("index.html")

  // Uncomment to open DevTools (for debugging)
  // mainWindow.webContents.openDevTools();

  mainWindow.on("closed", () => {
    mainWindow = null
  })
}

app.on("ready", createWindow)

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit()
})

app.on("activate", () => {
  if (mainWindow === null) createWindow()
})

// Comunicación con el renderer process
ipcMain.on("print-budget", () => {
  if (mainWindow) {
    // Configuración para impresión
    const options = {
      silent: false,
      printBackground: true,
      margins: {
        marginType: "custom",
        top: 0.4,
        bottom: 0.4,
        left: 0.4,
        right: 0.4,
      },
      landscape: false,
    }

    mainWindow.webContents.print(options, (success, reason) => {
      if (!success) {
        console.log(`Error al imprimir: ${reason}`)
      }
    })
  }
})
