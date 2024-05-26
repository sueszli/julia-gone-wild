from itertools import groupby
from operator import itemgetter


def schedule_tasks(task_durations):
    # fst: task_id, snd: duration
    sorted_tasks = sorted(enumerate(task_durations), key=lambda x: x[1], reverse=True)

    worker_utilization = [0] * 4  # time spent on work by each worker so far

    scheduled_tasks = []
    for task_id, duration in sorted_tasks:
        # get least utilized worker
        min_time = min(worker_utilization)
        worker_index = worker_utilization.index(min_time)

        # assign task
        worker_utilization[worker_index] += duration

        # keep track of assigned task
        start_time = min_time
        end_time = start_time + duration
        scheduled_tasks.append((worker_index, task_id, start_time, end_time))

    return scheduled_tasks


task_durations = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 4, 3, 3]
print(f"sorted tasks: {sorted(task_durations, reverse=True)}\n")
scheduled_tasks = schedule_tasks(task_durations)

# group tasks by worker
scheduled_tasks.sort(key=itemgetter(0))
for worker, tasks in groupby(scheduled_tasks, key=itemgetter(0)):
    print(f"worker {worker}:")
    for task in tasks:
        print(f"\ttask {task[1]}, start: {task[2]}, end: {task[3]} (duration: {task[3] - task[2]})")
    print()

# effective time
print(f"time spent: {max(map(itemgetter(3), scheduled_tasks))}")
