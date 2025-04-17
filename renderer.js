const { ipcRenderer } = require("electron")

// Lista de servicios predefinidos
const predefinedServices = [
  {
    id: 1,
    name: "Rectificación de Cigüeñal",
    description: "Rectificación completa de cigüeñal standard",
    price: 120.0,
  },
  { id: 2, name: "Rectificación de Block", description: "Rectificación de superficie de block", price: 90.0 },
  { id: 3, name: "Rectificación de Tapas de Bancada", description: "Alineado y rectificado de tapas", price: 75.0 },
  { id: 4, name: "Rectificación de Cilindros", description: "Rectificación y bruñido de cilindros", price: 25.0 },
  { id: 5, name: "Encamisado de Block", description: "Colocación de camisas en block", price: 40.0 },
  { id: 6, name: "Rectificación de Válvulas", description: "Rectificación de asientos de válvulas", price: 8.0 },
  { id: 7, name: "Válvulas Nuevas", description: "Reemplazo de válvulas por nuevas", price: 12.5 },
  { id: 8, name: "Asentado de Válvulas", description: "Asentado de válvulas en culata", price: 60.0 },
  { id: 9, name: "Guías de Válvulas Nuevas", description: "Reemplazo de guías de válvulas", price: 10.0 },
  {
    id: 10,
    name: "Rectificación de Tapa de Cilindros",
    description: "Rectificación de superficie de tapa",
    price: 85.0,
  },
]

// Establecer la fecha actual en el campo de fecha
document.getElementById("date").valueAsDate = new Date()

// Cargar servicios predefinidos
const servicesBody = document.getElementById("services-body")
const loadPredefinedServices = () => {
  servicesBody.innerHTML = ""
  predefinedServices.forEach((service) => {
    addServiceRow(service)
  })
  // Añadir una fila vacía para servicios personalizados
  addServiceRow({ id: "custom", name: "", description: "", price: 0 })
}

// Función para añadir una fila de servicio
function addServiceRow(service = { id: "custom", name: "", description: "", price: 0 }) {
  const row = document.createElement("tr")
  row.innerHTML = `
    <td><input type="checkbox" class="service-checkbox" data-price="${service.price}"></td>
    <td><input type="text" class="service-name" value="${service.name}"></td>
    <td><input type="text" class="service-description" value="${service.description}"></td>
    <td><input type="number" class="service-price" value="${service.price}" step="0.01" min="0"></td>
  `

  servicesBody.appendChild(row)

  // Añadir listeners a los nuevos inputs
  row.querySelector(".service-checkbox").addEventListener("change", updateTotals)
  row.querySelector(".service-price").addEventListener("input", updateTotals)
}

// Botón para añadir una nueva fila
document.getElementById("add-row-btn").addEventListener("click", () => {
  addServiceRow()
})

// Actualizar totales cuando se cambia un checkbox o un precio
function updateTotals() {
  let subtotal = 0

  // Seleccionar todos los checkboxes marcados
  const checkedServices = document.querySelectorAll(".service-checkbox:checked")

  // Calcular el subtotal basado en los servicios seleccionados
  checkedServices.forEach((checkbox) => {
    const row = checkbox.closest("tr")
    const priceInput = row.querySelector(".service-price")
    subtotal += Number.parseFloat(priceInput.value) || 0
  })

  // Calcular impuesto y total
  const tax = subtotal * 0.21 // 21% IVA
  const total = subtotal + tax

  // Actualizar los elementos en la UI
  document.getElementById("subtotal").textContent = `USD ${subtotal.toFixed(2)}`
  document.getElementById("tax").textContent = `USD ${tax.toFixed(2)}`
  document.getElementById("total").textContent = `USD ${total.toFixed(2)}`
}

// Imprimir presupuesto
document.getElementById("print-btn").addEventListener("click", () => {
  ipcRenderer.send("print-budget")
})

// Limpiar formulario (el botón reset ya maneja esto)
document.getElementById("clear-btn").addEventListener("click", () => {
  // Reiniciar los totales después de limpiar
  updateTotals()
})

// Guardar presupuesto (funcionalidad básica para demostración)
document.getElementById("save-btn").addEventListener("click", () => {
  alert("La funcionalidad de guardar se implementará en una versión futura.")
})

// Inicializar la aplicación
document.addEventListener("DOMContentLoaded", () => {
  loadPredefinedServices()
  updateTotals()
})
