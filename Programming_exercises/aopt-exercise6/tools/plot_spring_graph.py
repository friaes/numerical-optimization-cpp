#!/usr/bin/env python3
"""
Simple utility to plot spring graph CSV files produced by the project.

Usage examples:
  # specify prefix (will load <prefix>_nodes.csv and <prefix>_edges.csv)
  python3 tools/plot_spring_graph.py build/newton_std_5x5 -o build/newton_std_5x5.png

  # or explicitly provide nodes and edges csv paths
  python3 tools/plot_spring_graph.py --nodes build/newton_std_5x5_nodes.csv --edges build/newton_std_5x5_edges.csv -o build/newton_std_5x5.png

The script draws nodes and edges and saves a single PNG. It requires matplotlib and numpy.
"""
import argparse
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
import sys


def read_nodes(path):
    data = np.loadtxt(path, delimiter=',')
    if data.ndim == 1:
        data = data.reshape((1, -1))
    return data


def read_edges(path):
    data = np.loadtxt(path, delimiter=',')
    if data.ndim == 1:
        data = data.reshape((1, -1))
    return data


def plot_graph(nodes, edges, out_path, figsize=(6,6), title=None, show=False):
    fig, ax = plt.subplots(figsize=figsize)

    # draw edges
    for e in edges:
        i = int(e[0])
        j = int(e[1])
        xi = nodes[i]
        xj = nodes[j]
        ax.plot([xi[0], xj[0]], [xi[1], xj[1]], color='tab:gray', linewidth=1)

    # draw nodes
    ax.scatter(nodes[:,0], nodes[:,1], c='tab:blue', s=20, zorder=3)

    if title:
        ax.set_title(title)

    ax.set_aspect('equal', 'box')
    ax.axis('off')
    fig.tight_layout()
    fig.savefig(out_path, dpi=200)
    if show:
        plt.show()
    plt.close(fig)


def main():
    p = argparse.ArgumentParser(description='Plot spring graph CSV files (nodes + edges)')
    p.add_argument('prefix', nargs='?', help='prefix for files: <prefix>_nodes.csv and <prefix>_edges.csv')
    p.add_argument('--nodes', help='path to nodes csv (x,y per line)')
    p.add_argument('--edges', help='path to edges csv (i,j,length per line)')
    p.add_argument('-o', '--out', required=True, help='output PNG path')
    p.add_argument('--show', action='store_true', help='show the plot interactively')
    args = p.parse_args()

    nodes_path = None
    edges_path = None

    if args.nodes and args.edges:
        nodes_path = Path(args.nodes)
        edges_path = Path(args.edges)
    elif args.prefix:
        prefix = Path(args.prefix)
        nodes_path = prefix.with_name(prefix.name + '_nodes.csv') if prefix.suffix == '' else Path(str(prefix) + '_nodes.csv')
        # if user passed a path that already ends with _nodes.csv skip transformation
        if nodes_path.exists() is False:
            # try prefix_nodes.csv
            nodes_path = Path(str(prefix) + '_nodes.csv')
        edges_path = Path(str(prefix) + '_edges.csv')

    if nodes_path is None or edges_path is None:
        print('Error: either provide a prefix or both --nodes and --edges', file=sys.stderr)
        sys.exit(2)

    if not nodes_path.exists():
        print(f'Nodes file not found: {nodes_path}', file=sys.stderr)
        sys.exit(2)
    if not edges_path.exists():
        print(f'Edges file not found: {edges_path}', file=sys.stderr)
        sys.exit(2)

    nodes = read_nodes(nodes_path)
    edges = read_edges(edges_path)

    # Expect edges with at least first two columns (i, j). If there is a length column ignore it for plotting.
    if edges.shape[1] < 2:
        print('Edges file must contain at least two columns: i,j', file=sys.stderr)
        sys.exit(2)

    plot_graph(nodes, edges, args.out, title=str(nodes_path.stem))


if __name__ == '__main__':
    main()
