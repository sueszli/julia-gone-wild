def schedule_tasks(task_durations):
    sorted_tasks = sorted(enumerate(task_durations), key=lambda x: x[1])

    worker_availability = [0] * 4

    scheduled_tasks = []
    for task_id, duration in sorted_tasks:
        # find the worker who becomes available the soonest
        min_time = min(worker_availability)
        worker_index = worker_availability.index(min_time)

        # update worker availability
        worker_availability[worker_index] += duration

        # Record the assignment
        scheduled_tasks.append((worker_index, task_id, min_time, min_time + duration))

    return scheduled_tasks


task_durations = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 4, 3, 3]
scheduled_tasks = schedule_tasks(task_durations)

for worker, task_id, start_time, end_time in scheduled_tasks:
    print(f"Worker {worker}: Task {task_id}, Start: {start_time}, End: {end_time}")
