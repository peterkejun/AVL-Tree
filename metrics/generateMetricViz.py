import sys
import os
import pandas
import subprocess
import argparse
from matplotlib import pyplot
from matplotlib.pyplot import figure
from enum import Enum

parser = argparse.ArgumentParser(
    description="Generate avl performance graphs vs. binary search tree"
)

parser.add_argument(
    "--size",
    type=str,
    required="1000000",
    help="Size",
)

parser.add_argument(
    "--mode",
    type=str,
    default="0",
    help="Mode",
)

parser.add_argument(
    "--outputResultsPath",
    type=str,
    default="~/",
    help="Path",
)

def get_machine_mem() -> int:
    """
    Gets the RAM of the local machine.
    Args:
      None
    Returns:
      Integer representation of the local machine RAM in GBs
    """
    mem_info = subprocess.run(
        ["grep", "MemTotal", "/proc/meminfo"], stdout=subprocess.PIPE
    ).stdout.split()
    return int(int(mem_info[1]) / 1000000)

def run_test(
    size: int,
    mode: int,
    output_results_path: str,
) -> None:

    if not os.path.exists(output_results_path):
        os.makedirs(output_results_path)
    subprocess.call(
        [
            "sh",
            "./metricTest.sh",
            size,
            mode,
            output_results_path,
        ]
    )


def make_pidstat_tables(file_name: str, type: str) -> pandas.DataFrame:
    """
    Creates pandas tables from raw pidstat data.
    Args:
      file_name: Name of the .txt file containing raw pidstat output
    Returns:
      Pandas table with CPU, memory.
    """

    # Parse the raw .txt file into a pandas dataframe
    total_usage = []
    seconds_elapsed = 0

    with open(file_name) as f:
        for line in f:
            usage = []
            if line[0].isdigit():
                usage = line.split()
                usage.insert(0, seconds_elapsed)
                total_usage.append([seconds_elapsed, usage[9], usage[15]])
            elif line[0] == "#":
                seconds_elapsed += 1
    total_usage_df = pandas.DataFrame(
        total_usage,
        columns=[
            "Seconds Elapsed",
            type + " %CPU",
            type + " MEM",
        ],
    )
    total_usage_df[type + " MEM"] = total_usage_df[type + " MEM"].apply(
        lambda x: float(x) / 100 * get_machine_mem()
    )

    # Cast types of all columns
    for col in total_usage_df:
        total_usage_df[col] = total_usage_df[col].astype(float)

    total_usage_df[total_usage_df < 0] = 0

    return total_usage_df


def graph_pidstat(
    size: int, mode: int, output_results_path: str
) -> None:

    # Create pandas dataframes for all resource types and merge into one big dataframe
    binary_df = make_pidstat_tables(
        output_results_path
        + "/binary_test_stats_"
        + str(size)
        + "size_"
        + str(mode)
        + "mode.txt",
        "Binary",
    )
    avl_df = make_pidstat_tables(
        output_results_path
        + "/avl_test_stats_"
        + str(size)
        + "size_"
        + str(mode)
        + "mode.txt",
        "AVL",
    )

    # Generate graphs with resource usage information
    figure(figsize=(32, 20), dpi=80)
    pyplot.subplot(2, 1, 1)
    pyplot.plot(
        binary_df["Seconds Elapsed"],
        binary_df["Binary %CPU"],
        "-o",
        label="Binary",
    )
    pyplot.plot(
        avl_df["Seconds Elapsed"],
        avl_df["AVL %CPU"],
        "-o",
        label="Server",
    )

    pyplot.ylabel("%CPU Usage", fontsize=14)
    pyplot.legend()
    pyplot.title("BST VS AVL %CPU Usage", fontsize=14)

    pyplot.subplot(2, 1, 2)
    pyplot.plot(
        binary_df["Seconds Elapsed"],
        binary_df["Binary MEM"],
        "-o",
        label="Binary",
    )
    pyplot.plot(
        avl_df["Seconds Elapsed"],
        avl_df["AVL MEM"],
        "-o",
        label="AVL",
    )
    pyplot.ylabel("MEM Usage (GB)", fontsize=14)
    pyplot.legend()
    pyplot.title("BST vs AVL MEM Usage", fontsize=14)

    # Save the graph and csv files
    pyplot.savefig(
        output_results_path
        + "/resource_usage_"
        + str(size)
        + str(mode)
        + ".png"
    )

if __name__ == "__main__":
    args = parser.parse_args()
    run_test(
        args.size,
        args.mode,
        args.outputResultsPath,
    )
    graph_pidstat(args.size, args.mode, args.outputResultsPath)
    
    '''
    binary_df = make_pidstat_tables(
        args.outputResultsPath
        + "/binary_test_stats_"
        + str(args.size)
        + "size_"
        + str(args.mode)
        + "mode.txt",
        "Binary",
    )
    avl_df = make_pidstat_tables(
        args.outputResultsPath
        + "/avl_test_stats_"
        + str(args.size)
        + "size_"
        + str(args.mode)
        + "mode.txt",
        "AVL",
    )
    '''

    #print(avl_df)
    #print(binary_df)
    