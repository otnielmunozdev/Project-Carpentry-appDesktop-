CREATE TABLE distribuidores(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre TEXT,
num_distribuidor TEXT,
tipo_distribuidor TEXT
);
CREATE TABLE proovedores(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre TEXT,
num_proovedor TEXT,
tipo_proovedor TEXT
);
CREATE TABLE empleados(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre TEXT,
domicilio TEXT,
num_contacto INTEGER,
fecha_entrada DATE
);
CREATE TABLE pedido_costo(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre_pedido TEXT,
costo TEXT,
fecha_pedido DATE,
fecha_entrega DATE
);
CREATE TABLE clientes(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre TEXT,
domicilio TEXT,
num_contacto_cliente INTEGER
);
CREATE TABLE pedido(
id INTEGER PRIMARY KEY AUTOINCREMENT,
nombre_pedido TEXT,
fecha_pedido DATE,
fecha_entrega DATE,
especificaciones TEXT,
detalles TEXT,
costo TEXT,
prioridad TEXT,
id_cliente REFERENCES clientes(id)
);
