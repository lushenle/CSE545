package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"math/rand"
	"os"
	"os/exec"
	"strings"
	"time"
)

const alphabet = "abcdefghijklmnopqrstuvwxyz"

func init() {
	rand.Seed(time.Now().UnixNano())
}

// getMD5Hash get string md5sum
func getMD5Hash(text string) string {
	hash := md5.Sum([]byte(text))

	return hex.EncodeToString(hash[:])
}

// randomString generates a random string of length n
func randomString(n int) string {
	var sb strings.Builder
	k := len(alphabet)

	for i := 0; i < n; i++ {
		c := alphabet[rand.Intn(k)]
		sb.WriteByte(c)
	}

	return sb.String()
}

// randomInt generates a random integer between min and max
func randomInt(min, max int) int {
	return min + rand.Intn(max-min+1)
}

// run execute linux command
func run(command, arg string) error {
	cmd := exec.Command(command, arg)

	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	if err := cmd.Run(); err != nil {
		return err
	}

	return nil
}

func main() {
	for {
		text := randomString(randomInt(5, 20))
		md5sum := getMD5Hash(text)
		if md5sum[:2] == "00" {
			fmt.Printf("%v md5sum is: %v\n", text, md5sum)
			run("/challenge/main", text)
		}
	}
}
