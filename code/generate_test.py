import yaml

def read_test():
	data = yaml.load(open("tests/test_input.yml", 'r'), Loader=yaml.FullLoader)
	return data["graph"]

def create_test(test_data):
	test_name = test_data["NAME"] + ".txt"
	node_count = test_data["DIMENSION"]
	test_result = []
	
	for idx, node in enumerate(test_data["NODE_COORD_SECTION"][:-1]):
		for k_node in test_data["NODE_COORD_SECTION"][idx+1:]:
			_norma = ((k_node["node_x_coord"] - node["node_x_coord"]) ** 2 + (k_node["node_y_coord"] - node["node_y_coord"]) ** 2) ** 0.5
			test_result.append([node["node_id"], k_node["node_id"], int(_norma)])

	with open("tests/" + test_name, 'a') as file:
		file.write(f"{node_count} {len(test_result)}\n")
		for tern in test_result:
			file.write(f"{tern[0]} {tern[1]} {tern[2]}\n")
		file.close()
	return test_result

if __name__ == '__main__':
	create_test(read_test())