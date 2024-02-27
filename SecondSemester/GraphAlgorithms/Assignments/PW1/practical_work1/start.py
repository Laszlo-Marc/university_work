from domain.graph import Graph
from main import Console
from validation.validation import Validation

graph = Graph()
validation = Validation(graph)
console = Console( graph, validation)
console.start()
