class Fitness:
    def __init__(self, route):
        self.route = route
        self.distance = 0
        self.fitness = 0.0

    def route_distance(self):
        if self.distance == 0:
            path_distance = 0

            for index in range(len(self.route)):
                from_us = self.route[index]
                to_us = None
                if index + 1 < len(self.route):
                    to_us = self.route[index + 1]
                else:
                    to_us = self.route[0]
                # TO DO:
                # path_distance += from_us.distances(to_us["us_id"])
                path_distance += float(from_us['distances'][to_us['us_id']].replace(",", "."))
            self.distance = path_distance
        return self.distance

    def route_fitness(self):
        if self.fitness == 0:
            self.fitness = 1 / float(self.route_distance())
        return self.fitness
