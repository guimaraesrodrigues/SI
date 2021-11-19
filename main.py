import operator
import random
import json

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

from fitness import Fitness

MAX_GEN = 50  # Quantidade máxima de gerações
MUTATION_RATE = 0.01  # Porcentagem da taxa de mutação
POP_SIZE = 100  # Tamanho da população (conjunto de rotas possíveis)
ELITE_SIZE = 20  # Tamanho da elite  (melhores cromossomos para a próxima geração)


# Retorna uma rota aleatoria com base na lista de unidades de saúde
# Iniciando e terminando no CEMEPAR
def create_route(us_list):
    # , us_list[0] at the end
    route = [us_list[0], *random.sample(us_list[1:], len(us_list) - 1)]

    return route


def initial_population(us_list):
    population = []

    for i in range(0, POP_SIZE):
        population.append(create_route(us_list))

    return population


# retorna uma lista de rotas com fitness rankeados
def rank_routes(population):
    fitness_results = {}
    for i in range(0, len(population)):
        fitness_results[i] = Fitness(population[i]).route_fitness()

    return sorted(fitness_results.items(), key=operator.itemgetter(1), reverse=True)


# Seleciona os pais com a tecnica roulette wheel selection
def selection(population_ranked):
    selection_results = []

    df = pd.DataFrame(np.array(population_ranked), columns=["Index", "Fitness"])
    df['cum_sum'] = df.Fitness.cumsum()  # Return the cumulative sum
    df['cum_perc'] = 100 * df.cum_sum / df.Fitness.sum()

    # Seleciona os n melhores, onde n é ELITE_SIZE
    for i in range(0, ELITE_SIZE):
        selection_results.append(population_ranked[i][0])

    for i in range(0, len(population_ranked) - ELITE_SIZE):
        pick = 100 * random.random()
        for i in range(0, len(population_ranked)):
            if pick <= df.iat[i, 3]:
                selection_results.append(population_ranked[i][0])
                break
    return selection_results


def mating_pool(population, selection_results):
    matingpool = []
    for i in range(0, len(selection_results)):
        index = selection_results[i]
        matingpool.append(population[index])

    return matingpool


# ordered crossover
def breed(parent1, parent2):
    child_parent1 = []
    # exclui posicao 0 pois o ponto de partida não pode ser alterado na ordem do caminho
    allowed_values = list(range(1, len(parent1)))

    gene_a = random.choice(allowed_values)
    gene_b = random.choice(allowed_values)

    start_gene = min(gene_a, gene_b)
    end_gene = max(gene_a, gene_b)

    for i in range(start_gene, end_gene):
        child_parent1.append(parent1[i])

    child_parent2 = [item for item in parent2 if item not in child_parent1]

    return child_parent2[:start_gene] + child_parent1 + child_parent2[start_gene:]

    # return child_parent1 + child_parent2


def breed_population(matingpool):
    children = []
    length = len(matingpool) - ELITE_SIZE
    pool = random.sample(matingpool, len(matingpool))

    for i in range(0, ELITE_SIZE):
        children.append(matingpool[i])

    for i in range(0, length):
        child = breed(pool[i], pool[len(matingpool) - i - 1])
        children.append(child)
    return children


def mutate(individual):
    for swapped in range(1, len(individual)):
        if random.random() < MUTATION_RATE:
            swap_with = random.choice(list(range(1, len(individual))))

            if individual[swap_with]["us_id"] == "CM":
                print("swap_with", individual[swap_with])

            us_1 = individual[swapped]
            us_2 = individual[swap_with]

            individual[swapped] = us_2
            individual[swap_with] = us_1
    return individual


def mutate_population(population):
    mutated_pop = []

    for ind in range(0, len(population)):
        mutated_ind = mutate(population[ind])
        mutated_pop.append(mutated_ind)
    return mutated_pop


def get_next_generation(current_gen):
    population_ranked = rank_routes(current_gen)

    selection_results = selection(population_ranked)

    matingpool = mating_pool(current_gen, selection_results)

    children = breed_population(matingpool)

    next_generation = mutate_population(children)

    return next_generation


def genetic_algorithm(initial_pop):
    progress = []
    population = initial_population(initial_pop)
    initial_distance = 1 / rank_routes(population)[0][1]

    progress.append(initial_distance)
    print("Distancia inicial: " + str(initial_distance))

    for i in range(0, MAX_GEN):
        population = get_next_generation(population)
        progress.append(1 / rank_routes(population)[0][1])

    final_distance = str(1 / rank_routes(population)[0][1])
    print("Distancia final: " + final_distance)

    best_route_index = rank_routes(population)[0][0]
    best_route = population[best_route_index]

    plot_results(progress)

    return best_route


def plot_results(progress):
    plt.plot(progress)
    plt.ylabel('Distância (km)')
    plt.xlabel('Geração')
    plt.show()


def main():
    # abre arquivo com distancias
    # salva na memoria
    f = open('unidades.json', )
    data = json.load(f)

    best_route = genetic_algorithm(data)

    print("melhor rota: ")
    for index in range(len(best_route)):
        print(best_route[index]['us_name'])


if __name__ == '__main__':
    main()
