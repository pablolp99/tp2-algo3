import numpy as np
import pandas as pd

def create_test(n):
	nodes = np.arange(1, n+1)
	coords = np.arange(n, n*10)

	np.random.shuffle(coords)
	x_coord = pd.DataFrame(coords).sample(n)[0].to_list()
	np.random.shuffle(coords)
	y_coord = pd.DataFrame(coords).sample(n)[0].to_list()
	
	zipped = list(zip(x_coord, y_coord))
	zipped = pd.DataFrame(zipped).rename(columns={'index':'node_id', 0:'node_x_coord', 1:'node_y_coord'}).reset_index().to_numpy()
	
	test_name = "randomGraph_" + str(n) + ".txt"
	node_count = n
	test_result = []

	for idx, node in enumerate(zipped):
		for k_node in zipped[idx+1:]:
			_norma = ((k_node[0] - node[0]) ** 2 + (k_node[1] - node[1]) ** 2) ** 0.5
			test_result.append([node[0]+1, k_node[0]+1, int(_norma)])

	with open("tests/" + test_name, 'a') as file:
		file.write(f"{node_count} {len(test_result)}\n")
		for tern in test_result:
			file.write(f"{tern[0]} {tern[1]} {tern[2]}\n")
		file.close()
	return test_result


if __name__ == '__main__':
	create_test(10)
	create_test(100)
	create_test(200)
	create_test(300)
	create_test(350)