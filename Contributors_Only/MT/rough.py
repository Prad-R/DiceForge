import matplotlib.pyplot as plt

def read_data_from_file(freq):
    with open(freq, 'r') as file:
        data = [tuple(map(float, line.strip('()\n').split(','))) for line in file]

    return data

def plot_graph(data):
    x_values, y_values = zip(*data)

    # Plot the graph
    plt.axis([0,9,0,2000000])
    plt.plot(y_values, x_values, marker='o', linestyle='-')
    plt.title('graph of frequencies for 100000 numbers generated')
    plt.xlabel('remainder with 10')
    plt.ylabel('frequency')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    file_path = "freq"  
    data = read_data_from_file("freq.txt")

    

    plot_graph(data)
