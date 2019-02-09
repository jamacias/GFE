import math

def steering(x, y):
    # convert to polar
    r = math.hypot(x, y)
    print("r = ")
    print(r)
    t = math.atan2(y, x)
    print("t = ")
    print(t)

    # rotate by 45 degrees
    t -= math.pi / 4
    print("t = ")
    print(t)

    # back to cartesian
    left = r * math.cos(t)
    print("left = ")
    print(left)
    right = r * math.sin(t)
    print("right = ")
    print(right)

    # rescale the new coords
    left_rescale = left * math.sqrt(2)
    print("left_rescale = ")
    print(left_rescale)
    right_rescale = right * math.sqrt(2)
    print("right_rescale = ")
    print(right_rescale)

    if left_rescale == 0 or right_rescale == 0:
        # Do something
        print("Entered if ")
        left = (255*left_rescale)/1024
        right = (255*right_rescale)/1024
    # if (255*left_rescale)/512 > 255 or (255*right_rescale)/512 > 255
    #     left = (255*left_rescale)/((1024-512) + )
    #     right =
    else:
        left = (255*left_rescale)/512
        right = (255*right_rescale)/512

    # clamp to -255/+255
    # left = max(-255, min(left, 255))
    # right = max(-255, min(right, 255))

    return left, right

x = 200
y = 512
print(steering(x, y))
