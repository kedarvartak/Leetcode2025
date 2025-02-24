import pandas as pd

def dropDuplicateEmails(customers: pd.DataFrame) -> pd.DataFrame:

	customer_data = []
	hash_map = defaultdict(list)

	for index in customers.index:

		customer = customers.iloc[index]

		if customer['email'] not in hash_map:

			hash_map[customer['email']] = [customer['customer_id'],customer['name'],customer['email']]

	for key in hash_map:
		customer_data.append(hash_map[key])

	result = pd.DataFrame(customer_data , columns = ['customer_id', 'name' , 'email'])

	return result
	
