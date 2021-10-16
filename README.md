## Standard CCRP ( Capacity Constrained Route Planning )

## Input 

(1) A road network G = (N, E) where N is the set of nodes and E is the set of edges.

(2) S: set of source nodes, S ⊆ N. Evacuees are there in the source nodes.

(3) D: set of destination nodes, D ⊂ N. Evacuees need to be routed to the destination nodes.

(4) Number of evacuees known.

(5) Capacity of edges and nodes is known. Destination nodes have infinite capacity.

(6) Travel time between any two nodes is also known.

(7) Reservation tables will be maintained for all nodes and edges. These tables will store the capacities across the time series (from start to end of evacuation).

## Output 

Evacuation plan consisting of a set of origin-destination routes and scheduling of evacuees on each route.

## Objective 

Minimize evacuation egress time which is the time from the start of evacuation to the last evacuee reaching a destination 

## Constraints

(1) Every edge and node in the network have a capacity that can’t be violated.

(2) Capacity constraints and travel times are non-negative integers

(3) Reasonable Computation Time

(4) Evacuees start from and end up at nodes


## Algorithm for Standard CCRP 

  - Find the route with the earliest arrival time to any destination node from any source node, taking previous reservations and possible wait times into consideration. It is to be noted that this is the path with the earliest arrival time at a destination (starting from t=0). 

    - Also, it may happen that people may have to wait at the source to get the path with the earliest arrival at the destination.This can be done by using a generalized version of   Dijkstra’s algorithm. 

    - To avoid calculating the earliest arrival time route for every pair of source and destination nodes, a pseudo source node can be considered and edges with zero travel time and   infinite capacity can be added between the pseudo node and all other nodes in the network. 

    - In our implementation we haven't considered this and instead calculated earliest arrival path for all source destination pairs.

  - Allocate evacuees to that path i.e. min (number of current evacuees at source, available edge capacity (all edges on chosen route), available node capacity (all intermediate     nodes on chosen route))

  - Reserve the path by reducing the available capacity of edges and nodes on the chosen path by the number of evacuees considered.

  - Do the above steps while there are evacuees left to be routed.

   Since we are greedily assigning evacuees to the shortest route, this way we are trying to minimize the total egress time. This algorithm is fast, scalable, and produces good    routes, however, there are some drawbacks.

## Example Input 

N1 , N2 , N8 are the source nodes which contain the Evacuees .

N14 and N13 are the destination nodes.

![image](https://user-images.githubusercontent.com/23136178/137586153-a5324670-6df7-43d7-8f7b-a0ab77f38c31.png)

