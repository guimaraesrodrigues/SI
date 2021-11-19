class Fitness:
    def __init__(self, route):
        self.route = route
        self.distance = 0
        self.fitness = 0.0

    # Calcula distancia total de uma rota
    def route_distance(self):
        if self.distance == 0:
            path_distance = 0

            for index in range(len(self.route)):
                from_us = self.route[index]
                to_us = None
                if index + 1 < len(self.route):
                    to_us = self.route[index + 1]
                else:
                    # define o ponto inicial da rota como destino
                    to_us = self.route[0]

                # soma cumulativa das distancias entre from_us e to_us
                path_distance += float(from_us['distances'][to_us['us_id']].replace(",", "."))

            self.distance = path_distance
        return self.distance

    # Defina o quão boa é uma rota (distancia mais curta)
    def route_fitness(self):
        if self.fitness == 0:
            # Fitness representado como o inverso da distancia da rota.
            # Queremos minimizar a distancia total, logo um fitness com pontuacao grande é o melhor
            self.fitness = 1 / float(self.route_distance())
        return self.fitness
