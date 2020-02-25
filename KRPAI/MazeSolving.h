char path[100];

uint8_t path_length = 0;
uint8_t path_index = 0;

void recIntersection(char direction);
void simplifyPath(void);
void mazeOptimization(void);
void mazeTurn(char dir);

void recIntersection(char direction)
{
    path[path_length] = direction; // Store the intersection in the path variable.
    path_length++;
    simplifyPath(); // Simplify the learned path.
}

void simplifyPath()
{
    // only simplify the path if the second-to-last turn was a 'B'
    if (path_length < 3 || path[path_length - 2] != 'B')
        return;

    int totalAngle = 0;
    int i;
    
    for (i = 1; i <= 3; i++)
    {
        switch (path[path_length - i])
        {
            case 'R':
                totalAngle += 90;
                break;
            case 'L':
                totalAngle += 270;
                break;
            case 'B':
                totalAngle += 180;
                break;
        }
    }

    // Get the angle as a number between 0 and 360 degrees.
    totalAngle = totalAngle % 360;
    // Replace all of those turns with a single one.
    switch (totalAngle)
    {
        case 0:
            path[path_length - 3] = 'S';
            break;
        case 90:
            path[path_length - 3] = 'R';
            break;
        case 180:
            path[path_length - 3] = 'B';
            break;
        case 270:
            path[path_length - 3] = 'L';
            break;
    }
    // The path is now two steps shorter.
    path_length -= 2;
}

void mazeOptimization(void)
{
    // while (!status)
    // {
        // readLFSsensors();
        // switch (mode)
        // {
        //     case FOLLOWING_LINE:
        //         // followingLine();
        //         break;
        //     case CONT_LINE:
        //     case LEFT_TURN:
        //     case RIGHT_TURN:
        //         if (path_index >= path_length){
        //             // mazeEnd();
        //         } else {
        //             // mazeTurn(path[path_index]);
        //             path_index++;
        //         }
        //         break;
        // }
    // }
}

void mazeTurn(char dir)
{
    switch (dir)
    {
        case 'L': // Turn Left
            // goAndTurn(LEFT, 90);
            break;

        case 'R': // Turn Right
            // goAndTurn(RIGHT, 90);
            break;

        case 'B': // Turn Back
            // goAndTurn(RIGHT, 800);
            break;

        case 'S': // Go Straight
            // runExtraInch();
            break;
    }
}
