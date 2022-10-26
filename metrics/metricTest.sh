# Example usage:
# sh metricsTest.sh [size] [mode] [output results path]

set -e

echo "Starting binary search tree test with $1 size, $2 mode, path: $3"
g++ metricTestBinary.cc
./a.out $1 $2 2>&1 & 
pidstat 1 -r -u -d -h -p $! > $3/binary_test_stats_$1size_$2mode.txt
binary_monitor_pid=$!

#Launch batch test
echo "Starting avl batch test with $1 size, $2 mode, path: $3"
g++ metricTest.cc
./a.out $1 $2 2>&1 & 
pidstat 1 -r -u -d -h -p $! > $3/avl_test_stats_$1size_$2mode.txt

#Stop all pidstat jobs 
echo "Batch test complete..."