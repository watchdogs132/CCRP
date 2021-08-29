### CCRP (Capacity Constrained Route Planning )

  - Find the route with the earliest arrival time to any destination node from any source node, taking previous reservations and possible wait times into consideration

  - Allocate evacuees to that path and reserve that path.

  - Do this while there are evacuees left to be routed.

  - Since we are greedily assigning evacuees to the shortest route , this way we are trying to minimize the total egress time.

### Things to Consider 

  - We have a spatial network with some nodes and edges .

  - Source Nodes : These nodes have evacuees in them .

  - Destination Nodes: Evacuees need to be routed to the destination nodes. 

  - Priority Nodes: Waiting time of evacuees in these nodes need to be minimized .

  - Edges and nodes have capacities which can not be violated. We keep of track of these capacities at each time step . 
  
  - Destination nodes are assumed to have a very large capacity.

  - Number of evacuees that can travel through a path is considered to be the minimum of the capacities of the nodes and edges on that path.

  - Time taken to traverse any edge is available and waiting time at any node is also taken into account when calculating the shortest path between any source and destination.


#### Input Graph 

![image](https://user-images.githubusercontent.com/23136178/131255201-2df0ff55-d4b6-4c10-a175-6531c1a5415e.png)

